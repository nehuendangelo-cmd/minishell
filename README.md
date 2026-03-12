
Projet : Minishell
Compilation : make 
Lancement : ./minishell

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


### les differentes redirections

https://medium.com/@boris.alexandre.rose/linux-shell-les-flux-de-redirection-1b6ffbad9e71
