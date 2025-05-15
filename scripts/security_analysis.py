import subprocess


def run_sh_commands(commands):
    results = []

    for command in commands:
        try:
            result = subprocess.run(
                command,
                shell=True,
                check=False,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True
            )
            results.append({
                'command': command,
                'returncode': result.returncode,
                'stdout': result.stdout.strip(),
                'stderr': result.stderr.strip()
            })
        except Exception as e:
            results.append({
                'command': command,
                'returncode': -1,
                'stdout': '',
                'stderr': str(e)
            })

    return results




class SecurityAnalysis:
    def __init__(self):
        results = run_sh_commands(commands)

        for r in results:
            print(f"Command: {r['command']}")
            print(f"Return code: {r['returncode']}")
            print(f"Output: {r['stdout']}")
            print(f"Error: {r['stderr']}\n")

commands = [
    # Database creation starting from code
    # r'codeql database create python_example_db --language=python --source-root="/Users/matteocicalese/PycharmProjects/SecurePromptSlicing/llm_sec_eval_dataset/LLMSecEval-main/Dataset/Secure Code Samples/cwe-798"',

    # Query download and installation for C/C++, Python and Java
    # r'codeql pack download codeql/cpp-queries -d "/Users/matteocicalese/PycharmProjects/SecurePromptSlicing/CodeQL/Queries/c"'
    # r'codeql pack download codeql/python-queries -d "/Users/matteocicalese/PycharmProjects/SecurePromptSlicing/CodeQL/Queries/py"'
    # r'codeql pack download codeql/java-queries -d "/Users/matteocicalese/PycharmProjects/SecurePromptSlicing/CodeQL/Queries/java"'
    r'codeql pack install -- "/Users/matteocicalese/PycharmProjects/SecurePromptSlicing/CodeQL/Queries/c/codeql/cpp-queries/1.3.9"',
    r'codeql pack install -- "/Users/matteocicalese/PycharmProjects/SecurePromptSlicing/CodeQL/Queries/py/codeql/python-queries/1.4.8"',
    r'codeql pack install -- "/Users/matteocicalese/PycharmProjects/SecurePromptSlicing/CodeQL/Queries/java/codeql/java-queries/1.4.2"',

    # Database analysis using downloaded query pack
    # r'',
    r'codeql database analyze "/Users/matteocicalese/PycharmProjects/SecurePromptSlicing/CodeQL/python_example_db" --format=csv --output="/Users/matteocicalese/PycharmProjects/SecurePromptSlicing/results_codeql/python_results_sec_extended.csv" "/Users/matteocicalese/PycharmProjects/SecurePromptSlicing/CodeQL/Queries/py" --warnings=hide'
    # r''
]

SecurityAnalysis()
