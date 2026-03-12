
*This project has been created as part of the 42 curriculum by nd-angel, khderdou.*

Projet : Minishell
Compilation : make 
Lancement : ./minishell

# description

## partie front-end

Partie réalisée : parsing + gestion des variables d'environnement

Parsing

Le parsing transforme la ligne de commande entrée par l'utilisateur en tokens, applique l'expansion des variables, puis construit une liste de commandes (`t_cmd`) exploitable par l'execution.

Le parser est organisé en plusieurs fichiers afin de séparer les responsabilités.

Structure du parsing

build.c : construction de la liste de commandes (args + redirections) a partir des tokens

char.c : validation des operateurs/separateurs et utilitaires de lecture des caracteres (espaces, quotes)

free.c : liberation de la memoire des tokens, commandes, redirections et tableaux de chaines

missing.c : utilitaires de tokenisation (operateurs + creation/ajout de tokens quotes)

parse.c : orchestration du parsing (pre-check syntaxe, tokenisation, expansion, build des commandes)

quote.c : verification de fermeture des quotes et indication d'expansion selon le type de quote

string.c : helpers de chaines dedies au shell (substr/join/compare/tests)

syntaxe.c : verification de la syntaxe des pipes et redirections (debut/fin/invalides)

tok2.c : expansion des variables sur les tokens WORD (sauf en quotes simples)

token.c : creation/ajout des tokens operateurs et mots non quotes

utils.c : expansion des variables d'environnement et helpers lies aux redirections

utils2.c : helpers de chaines avec gestion memoire + fonction d'erreur

Étapes du parsing

*   Lecture de la ligne de commande
*   Découpage en tokens
*   Gestion des quotes
*   Vérification de la syntaxe

Le parser vérifie les erreurs comme :

- pipe au debut ou a la fin
- `||` (pipe double invalide)
- redirection invalide (ex. pas de mot/fichier valide apres `<`, `>`, `<<`, `>>`)

*   Création de la liste chaînée de tokens


Une fonction centrale "appel_parse" regroupe toutes les etapes du parsing et est appelée dans `main`, ce qui simplifie l'integration entre la partie front-end et la partie back-end.

#ressources front-end:

https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html

https://abhijit-pal.medium.com/demystifying-bash-command-line-processing-a-seven-step-journey-74287e1c635c

https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf

https://medium.com/@WinnieNgina/guide-to-code-a-simple-shell-in-c-bd4a3a4c41cd

https://www.gnu.org/software/bash/manual/html_node/Definitions.html


## partie backend

Partie réalisée : execution des commandes, gestion des pipes, builtins

The backend part receivce a t_cmd struct from the parse part. it is filled with the list of cmd to execute, and there redirections.

The main goal of the backend part (execute part) is to execute the commands, exit with the same codes as the original shell.

To do so, it first need to identify the command : there is the builtins, which are hardcoded, and there is the other functions which have a pathway.
We also need to identify the number of commands, if there is only one, we handle it with a specific function (execute_single_cmd).
Why ? Because in this case we don't need to make a pipeline.
Otherwise, we use execute_pipeline, which contains a loop while (cmd).

For the builtins, we call our functions we coded ourselves.

For the others, we find their path, and then we execute them using the execve function.

### Structure de l'executor

executor.c : check and launch appropriate functions if heredocs, if !cmd, if single builtin, if single cmd

path.c : find the path of a given command so execve can execute it

pipeline.c : monitor the pieline, make pipes, make childs, waitpid all

set_childs.c : set the childs, weither it is the first, a middle, or the last one

### Execute_pipeline

at each tour of while (cmd) :

*   we check if the cmd is the last, if not, we create a pipe which will redirect the output of the cmd to the input of the next one.
*   Then we create a child, it is a process that will execute in parralel, with it's own copy of the parent process.
*   We will execute the cmd in the child, so we can handle an exit correctly.
*   with the sigaction command, we put the SIGINT (ctrl + c) and SIGUQUIT (ctrl + \) back to their default behavior.
    Why ? because SIGINT and SIGUQUIT will close the child, and we will continue to execute the other commands. That is the behavior of bash. Only the exit code of the last command is catched and returned.

### builtins

The most important is they execute in the parent, not in a child.

Builtins are commands that have to modify the shell in itself.

For exemple : cd has to modify $PWD and $OLDPWD of the shell.

To do so, they must not be executed in a child with exceve, because it would not modify the shell but only a copy of it.

that is why the builtins are "built in" the shell, so they can be directly executed in the parent.


# instruction


# ressources backend


- Writing your own shell
explique la logique lexing → parsing → expansion → execution
 https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf

- utilisation de Git
    - https://learngitbranching.js.org/?locale=fr_FR
    - https://www.atlassian.com/fr/git/tutorials/comparing-workflows/gitflow-workflow
    - Bien nommer ses commit : https://buzut.net/cours/versioning-avec-git/bien-nommer-ses-commits
    - https://think-like-a-git.net/

- video
 [Let’s build a super simple shell in C](https://www.youtube.com/watch?v=yTR00r8vBH8)

- les differentes redirections
https://medium.com/@boris.alexandre.rose/linux-shell-les-flux-de-redirection-1b6ffbad9e71

- For the backend part, Claude Sonnet 4.6 has been used as a professor that never write code
 but explain the concepts behind building a shell.