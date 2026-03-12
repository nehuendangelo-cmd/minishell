*This project has been created as part of the 42 curriculum by nd-angel, khderdou.*

# Minishell

A 42 project coded by nd-angel and khderdou.

Goal: recreate a mini bash in C.

---

## Description

### Front-end part

Implemented part: prompt + parsing + expansion.

The front-end reads the user input with `readline`, checks syntax, tokenizes the line, expands variables, then builds the `t_cmd` list sent to the executor.

### Prompt / history

- `readline("minishell$")` to read the command line.
- `add_history(line)` when the line is not empty.
- `Ctrl-C` resets a clean prompt.

### Parsing (simple)

- syntax pre-check: pipe at start/end, `||`, invalid redirection.
- tokenization: words + operators (`|`, `<`, `>`, `<<`, `>>`).
- quote handling while reading the line.
- final build of a linked list of `t_cmd`.

### Expansion

- expansion of `$VAR` and `$?`.
- no expansion inside single quotes.
- removal of empty unquoted tokens after expansion.

---

## Instructions

```bash
make
./minishell
```

---

### Back-end part

Implemented part: command execution, pipes handling, builtins.

The backend part receivce a t_cmd struct from the parse part. it is filled with the list of cmd to execute, and there redirections.

The main goal of the backend part (execute part) is to execute the commands, exit with the same codes as the original shell.

To do so, it first need to identify the command : there is the builtins, which are hardcoded, and there is the other functions which have a pathway. We also need to identify the number of commands, if there is only one, we handle it with a specific function (execute_single_cmd). Why ? Because in this case we don't need to make a pipeline. Otherwise, we use execute_pipeline, which contains a loop while (cmd).

For the builtins, we call our functions we coded ourselves.

For the others, we find their path, and then we execute them using the execve function.

### Executor structure

- executor.c : check and launch appropriate functions if heredocs, if !cmd, if single builtin, if single cmd
- path.c : find the path of a given command so execve can execute it
- pipeline.c : monitor the pieline, make pipes, make childs, waitpid all
- set_childs.c : set the childs, weither it is the first, a middle, or the last one

### Execute_pipeline

at each tour of while (cmd) :

- we check if the cmd is the last, if not, we create a pipe which will redirect the output of the cmd to the input of the next one.
- Then we create a child, it is a process that will execute in parralel, with it's own copy of the parent process.
- We will execute the cmd in the child, so we can handle an exit correctly.
- with the sigaction command, we put the SIGINT (ctrl + c) and SIGUQUIT (ctrl + ) back to their default behavior. Why ? because SIGINT and SIGUQUIT will close the child, and we will continue to execute the other commands. That is the behavior of bash. Only the exit code of the last command is catched and returned.

### Builtins

The most important is they execute in the parent, not in a child.

Builtins are commands that have to modify the shell in itself.

For exemple : cd has to modify $PWD and $OLDPWD of the shell.

To do so, they must not be executed in a child with exceve, because it would not modify the shell but only a copy of it.

that is why the builtins are "built in" the shell, so they can be directly executed in the parent.

## Resources

### Front-end resources

- [POSIX Shell specification](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html)
- [Demystifying bash command line processing](https://abhijit-pal.medium.com/demystifying-bash-command-line-processing-a-seven-step-journey-74287e1c635c)
- [Writing your own shell (Purdue)](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
- [Guide to code a simple shell in C](https://medium.com/@WinnieNgina/guide-to-code-a-simple-shell-in-c-bd4a3a4c41cd)
- [GNU Bash definitions](https://www.gnu.org/software/bash/manual/html_node/Definitions.html)

### Back-end resources

- [Writing your own shell (lexing → parsing → expansion → execution)](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
- Git resources:
    - [Learn Git Branching](https://learngitbranching.js.org/?locale=fr_FR)
    - [Atlassian Gitflow workflow](https://www.atlassian.com/fr/git/tutorials/comparing-workflows/gitflow-workflow)
    - [Bien nommer ses commits](https://buzut.net/cours/versioning-avec-git/bien-nommer-ses-commits)
    - [Think like a git](https://think-like-a-git.net/)
- [Video: Let’s build a super simple shell in C](https://www.youtube.com/watch?v=yTR00r8vBH8)
- [Linux shell redirections](https://medium.com/@boris.alexandre.rose/linux-shell-les-flux-de-redirection-1b6ffbad9e71)

### AI usage

- AI tool/model used: Claude Sonnet 4.6.
- How it was used: as a professor-like assistant to explain concepts, not to replace implementation.
- Parts concerned: mainly back-end understanding (execution flow, pipes, redirections).
