# Tests Minishell - Guide Complet

## 📋 Table des matières
1. [Tests de Parsing](#tests-de-parsing)
2. [Tests des Builtins](#tests-des-builtins)
3. [Tests des Redirections](#tests-des-redirections)
4. [Tests des Pipes](#tests-des-pipes)
5. [Tests des Variables d'Environnement](#tests-des-variables-denvironnement)
6. [Tests des Signaux](#tests-des-signaux)
7. [Tests des Quotes](#tests-des-quotes)
8. [Tests de l'Exit Status](#tests-de-lexit-status)
9. [Tests Edge Cases](#tests-edge-cases)

---

## 🔍 Tests de Parsing

### Syntaxe basique
```bash
# Commandes simples
ls
ls -la
echo hello

# Espaces multiples (doivent être gérés)
ls    -l     -a
echo    "test"

# Erreurs de syntaxe à détecter
|
||
| ls
ls |
ls | | cat
< >
> <
```

**Attentes :** Les erreurs de syntaxe doivent afficher `syntax error` et ne pas exécuter.

---

## 🛠️ Tests des Builtins

### `echo`
```bash
echo hello world
echo "hello world"
echo 'hello world'
echo -n hello        # Sans newline
echo -n -n test      # Double -n
echo -nnnnn test     # Multiple n
echo $USER           # Variable expansion
echo "$USER"         # Dans double quotes
echo '$USER'         # Dans single quotes (pas d'expansion)
echo                 # Juste un newline
```

**Attentes :**
- `-n` supprime le retour à la ligne
- Expansion des variables sauf dans single quotes

### `pwd`
```bash
pwd
cd /tmp
pwd
cd ~
pwd
```

**Attentes :** Affiche toujours le chemin absolu courant.

### `cd`
```bash
cd /tmp
pwd                  # Doit afficher /tmp
cd ~
pwd                  # Doit afficher $HOME
cd ..
pwd
cd -                 # Retour au dossier précédent (bonus)
cd /nonexistent      # Erreur
cd                   # Va à $HOME
```

**Attentes :**
- `cd` seul va à HOME
- `cd ..` remonte d'un niveau
- Erreur si le dossier n'existe pas

### `env`
```bash
env                  # Affiche toutes les variables
env | grep PATH      # Teste avec pipe
```

**Attentes :** Liste toutes les variables d'environnement.

### `export`
```bash
export TEST=hello
echo $TEST           # Doit afficher "hello"
export TEST2="hello world"
echo $TEST2
export TEST3        # Sans valeur (valide)
env | grep TEST
export              # Affiche toutes les variables exportées
export =value       # Erreur : nom invalide
export 123=value    # Erreur : nom invalide
```

**Attentes :**
- Variables créées disponibles dans `env`
- Noms invalides = erreur

### `unset`
```bash
export TEST=hello
echo $TEST           # Affiche "hello"
unset TEST
echo $TEST           # Affiche rien
unset PATH           # Doit supprimer PATH
ls                   # Ne devrait plus fonctionner
```

**Attentes :** Variable disparaît complètement.

### `exit`
```bash
exit                 # Exit avec code 0
exit 42              # Exit avec code 42
exit 300             # Code = 300 % 256 = 44
exit abc             # Erreur, exit avec 2
exit 1 2 3           # Erreur "too many arguments"
```

**Attentes :**
- Code de sortie entre 0-255
- Erreur si argument non numérique

---

## 📂 Tests des Redirections

### Redirection de sortie `>`
```bash
echo hello > out.txt
cat out.txt          # Doit afficher "hello"
ls > files.txt
cat files.txt
> out.txt            # Fichier vide créé
cat out.txt          # Fichier vide
```

**Attentes :**
- Crée/écrase le fichier
- Permissions par défaut : 0644

### Redirection append `>>`
```bash
echo hello > out.txt
echo world >> out.txt
cat out.txt          # Doit afficher "hello\nworld"
```

**Attentes :** Ajoute à la fin sans écraser.

### Redirection d'entrée `<`
```bash
echo "test content" > in.txt
cat < in.txt         # Doit afficher "test content"
wc -l < in.txt       # Compte les lignes
< nonexistent        # Erreur : fichier introuvable
```

**Attentes :**
- Lit depuis le fichier
- Erreur si fichier inexistant

### Heredoc `<<`
```bash
cat << EOF
hello
world
EOF
# Doit afficher "hello\nworld"

cat << STOP | grep hello
hello
world
STOP
# Doit afficher "hello"

cat << EOF > out.txt
line1
line2
EOF
cat out.txt
```

**Attentes :**
- Lit jusqu'au délimiteur
- Variables expansées sauf dans quotes

### Redirections multiples
```bash
< in.txt cat > out.txt
cat < in1.txt < in2.txt    # Dernière redirection gagne
echo test > out1.txt > out2.txt  # Écrit dans out2.txt
```

---

## 🔗 Tests des Pipes

### Pipes simples
```bash
ls | wc -l
cat file.txt | grep test
echo hello | cat
```

### Pipes multiples
```bash
ls -l | grep txt | wc -l
cat file.txt | grep test | sort | uniq
```

### Pipes + redirections
```bash
ls | grep test > out.txt
< in.txt cat | grep hello > out.txt
```

### Pipes avec builtins
```bash
export TEST=hello | echo done
echo test | cd /tmp
env | grep PATH
```

**Attentes :**
- Builtins dans pipes s'exécutent dans subshells
- `export`, `cd`, `unset` n'affectent pas le shell parent si dans un pipe

---

## 🌍 Tests des Variables d'Environnement

### Expansion basique
```bash
echo $USER
echo $HOME
echo $PATH
echo $NONEXISTENT    # Affiche rien
```

### Expansion dans quotes
```bash
echo "$USER"         # Expansion
echo '$USER'         # Pas d'expansion, affiche littéral
echo "User: $USER, Home: $HOME"
```

### Exit status `$?`
```bash
ls
echo $?              # 0 (succès)
ls /nonexistent
echo $?              # 2 (erreur)
false
echo $?              # 1
```

### Variables sans expansion
```bash
echo \$USER          # Affiche "$USER"
echo \\$USER         # Affiche "\username"
```

---

## 🚦 Tests des Signaux

### CTRL+C (SIGINT)
```bash
# Dans le prompt, tapez CTRL+C
# Comportement attendu : nouvelle ligne, nouveau prompt

cat
# Tapez CTRL+C pendant que cat attend
# Comportement : cat s'arrête, nouveau prompt
```

### CTRL+\ (SIGQUIT)
```bash
# Dans le prompt, tapez CTRL+\
# Comportement attendu : rien (signal ignoré)

cat
# Tapez CTRL+\ pendant que cat attend
# Comportement : cat affiche "Quit" et s'arrête
```

### CTRL+D (EOF)
```bash
# Dans le prompt, tapez CTRL+D
# Comportement attendu : minishell se ferme (comme bash)
```

**Attentes :**
- SIGINT (CTRL+C) : nouveau prompt, pas de quit
- SIGQUIT (CTRL+\) : ignoré dans le prompt
- EOF (CTRL+D) : ferme le shell

---

## 💬 Tests des Quotes

### Single quotes `'`
```bash
echo 'hello $USER'   # Affiche "hello $USER" (littéral)
echo 'test\n'        # Affiche "test\n" (pas d'interprétation)
```

### Double quotes `"`
```bash
echo "hello $USER"   # Expansion de variable
echo "test\n"        # Selon implémentation (souvent littéral)
echo "hello   world" # Espaces préservés
```

### Quotes non fermées
```bash
echo "hello
# Doit afficher une erreur ou attendre la fermeture
```

### Quotes mixtes
```bash
echo "hello '$USER'"     # Affiche "hello '$USER'"
echo 'hello "$USER"'     # Affiche 'hello "$USER"'
echo "l'apostrophe"      # OK
echo 'guillemet"'        # OK
```

---

## 🎯 Tests de l'Exit Status

```bash
ls
echo $?              # 0

ls /nonexistent 2>/dev/null
echo $?              # 2

false
echo $?              # 1

true
echo $?              # 0

exit 42
# Dans un nouveau shell : echo $? devrait donner 42
```

---

## 🧪 Tests Edge Cases

### Commandes vides
```bash
# Taper Entrée sans rien
# Comportement : nouveau prompt

   
# Espaces seulement
# Comportement : nouveau prompt
```

### Commandes inexistantes
```bash
commandeQuiNexistePas
echo $?              # 127
```

### PATH modifié
```bash
export PATH=/bin
ls                   # Devrait fonctionner
export PATH=/tmp
ls                   # Devrait échouer (command not found)
```

### Commandes avec chemin absolu
```bash
/bin/ls
/usr/bin/env
./minishell          # Lance une copie de minishell
```

### Fichiers avec permissions
```bash
echo "echo test" > script.sh
chmod +x script.sh
./script.sh          # Doit exécuter

echo "echo test" > noperm.sh
chmod -x noperm.sh
./noperm.sh          # Erreur permission denied
```

### Très longues commandes
```bash
echo aaaaaaaaaa...   # 1000+ caractères
ls -l -a -h -R ...   # Beaucoup d'arguments
```

### Caractères spéciaux dans les noms
```bash
touch "file with spaces.txt"
cat "file with spaces.txt"
rm "file with spaces.txt"
```

---

## 📝 Checklist de validation

### Obligatoire
- [ ] Parsing correct (pas de crash)
- [ ] Tous les builtins fonctionnent
- [ ] Redirections `< > >> <<`
- [ ] Pipes simples et multiples
- [ ] Variables `$VAR` et `$?`
- [ ] Quotes simples et doubles
- [ ] Signaux CTRL+C, CTRL+D, CTRL+\
- [ ] Gestion des erreurs propre
- [ ] Pas de leaks mémoire
- [ ] Exit codes corrects

### Tests de comparaison avec bash
Pour chaque test, compare le résultat avec bash :
```bash
# Dans bash
ls | wc -l > bash_out.txt

# Dans minishell
ls | wc -l > mini_out.txt

# Compare
diff bash_out.txt mini_out.txt
```

---

## 🐛 Outils de debug

### Valgrind (leaks mémoire)
```bash
valgrind --leak-check=full --show-leak-kinds=all ./minishell
```

### Leaks sur macOS
```bash
leaks -atExit -- ./minishell
```

### Tests automatisés
Tu peux créer un script `test.sh` :
```bash
#!/bin/bash
echo "=== Test echo ==="
echo "echo hello" | ./minishell
echo "echo hello" | bash

echo "=== Test pipes ==="
echo "ls | wc -l" | ./minishell
echo "ls | wc -l" | bash
```

---

## 💡 Conseils

1. **Teste au fur et à mesure** : ne code pas tout avant de tester
2. **Compare avec bash** : c'est ta référence
3. **Vérifie les leaks** : chaque malloc doit avoir son free
4. **Gère les erreurs** : chaque syscall peut échouer
5. **Teste les edge cases** : vide, NULL, très long, etc.
6. **Utilise des scripts** : automatise les tests répétitifs

Bon courage ! 🚀
