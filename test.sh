#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
NC='\033[0m'

PASS=0
FAIL=0

echo -e "${BLUE}=== Minishell Mandatory Test Suite ===${NC}"

normalize_mini_output() {
    local cmd_file="$1"
    sed 's/minishell\$//g' \
    | awk 'NF > 0' \
    | awk 'FNR == NR {ignore[$0]=1; next} !($0 in ignore)' "$cmd_file" -
}

run_mini_script() {
    local cmd_file="$1"
    ./minishell < "$cmd_file" 2>&1 | normalize_mini_output "$cmd_file"
}

run_bash_script() {
    local cmd_file="$1"
    bash < "$cmd_file" 2>&1 | awk 'NF > 0'
}

compare_script() {
    local title="$1"
    local content="$2"

    printf "%s\n" "$content" > .mini_cmds.tmp
    run_mini_script .mini_cmds.tmp > .mini_out.tmp
    run_bash_script .mini_cmds.tmp > .bash_out.tmp

    echo -e "\n${BLUE}${title}${NC}"
    if [ "$(cat .mini_out.tmp)" = "$(cat .bash_out.tmp)" ]; then
        echo -e "${GREEN}✓ PASS${NC}"
        PASS=$((PASS + 1))
    else
        echo -e "${RED}✗ FAIL${NC}"
        echo "Minishell output:"
        cat .mini_out.tmp
        echo "Bash output:"
        cat .bash_out.tmp
        FAIL=$((FAIL + 1))
    fi
}

expect_error() {
    local title="$1"
    local content="$2"
    local regex="$3"

    printf "%s\n" "$content" > .mini_cmds.tmp
    run_mini_script .mini_cmds.tmp > .mini_out.tmp

    echo -e "\n${BLUE}${title}${NC}"
    if grep -Eqi "$regex" .mini_out.tmp; then
        echo -e "${GREEN}✓ PASS${NC}"
        PASS=$((PASS + 1))
    else
        echo -e "${RED}✗ FAIL${NC}"
        echo "Output reçu:"
        cat .mini_out.tmp
        FAIL=$((FAIL + 1))
    fi
}

echo -e "\n${YELLOW}-- Build --${NC}"
if make -s && make -s clean && make -s; then
    echo -e "${GREEN}✓ Build targets OK${NC}"
    PASS=$((PASS + 1))
else
    echo -e "${RED}✗ Build failed${NC}"
    FAIL=$((FAIL + 1))
fi

echo -e "\n${YELLOW}-- Parsing / Syntax --${NC}"
expect_error "Syntax error: pipe seul" "|" "error|syntax"
expect_error "Syntax error: redirection incomplète" "echo >" "error|syntax"

echo -e "\n${YELLOW}-- Execution / PATH --${NC}"
compare_script "Commande simple echo" "echo hello world"
compare_script "Commande absolue" "/bin/echo ok"
expect_error "Commande inconnue" "this_command_does_not_exist" "not found|introuvable"

echo -e "\n${YELLOW}-- Builtins obligatoires --${NC}"
compare_script "echo -n" "echo -n hello"
compare_script "pwd" "pwd"
compare_script "env | grep USER" "env | grep USER"
compare_script "cd + pwd" "pwd
cd /tmp
pwd"
compare_script "export/unset" "export TEST_MINI=42
echo \$TEST_MINI
unset TEST_MINI
echo \$TEST_MINI"

echo -e "\n${YELLOW}-- Redirections --${NC}"
compare_script "Redirection sortie >" "echo test > /tmp/mini_out_file
cat /tmp/mini_out_file"
compare_script "Redirection entrée <" "cat < /etc/hostname"
compare_script "Append >>" "echo one > /tmp/mini_append
echo two >> /tmp/mini_append
cat /tmp/mini_append"

echo -e "\n${YELLOW}-- Pipes --${NC}"
compare_script "Pipe simple" "ls | wc -l"
compare_script "Pipes multiples" "printf 'a\nb\na\n' | sort | uniq | wc -l"

echo -e "\n${YELLOW}-- Variables / Quotes / Exit status --${NC}"
compare_script "Expansion variable" "echo \$USER"
compare_script "Single quote (pas d'expansion)" "echo 'hello \$USER'"
compare_script "Double quote (expansion)" "echo \"hello \$USER\""
compare_script "Exit status \$?" "ls /definitely_not_here
echo \$?"

rm -f .mini_cmds.tmp .mini_out.tmp .bash_out.tmp
rm -f /tmp/mini_out_file /tmp/mini_append

echo -e "\n${BLUE}=== Résumé ===${NC}"
echo -e "${GREEN}PASS: ${PASS}${NC}"
echo -e "${RED}FAIL: ${FAIL}${NC}"

echo -e "\n${YELLOW}Checks manuels (non automatisés):${NC}"
echo "- Signaux interactifs: Ctrl-C, Ctrl-\\, Ctrl-D"
echo "- Leaks mémoire: valgrind / leaks"

if [ "$FAIL" -gt 0 ]; then
    exit 1
fi

exit 0
