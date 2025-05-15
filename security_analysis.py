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
    r'cd prova_c',
    r'rm -f *.o vuln',
    r'cd ..',

    # Database creation starting from code
    r'codeql database create CodeQL/Databases/python_example_db --language=python --source-root=prova_python --overwrite',
    r'codeql database create CodeQL/Databases/c_example_db --language=c --source-root=prova_c --overwrite',
    r'codeql database create CodeQL/Databases/java_example_db --language=java --source-root=prova_java --command="mvn clean compile" --overwrite',

    # Query download and installation for C/C++, Python and Java
    r'codeql pack download codeql/python-queries',
    r'codeql pack download codeql/cpp-queries',
    r'codeql pack download codeql/java-queries',

    # Database analysis using downloaded query pack
    r'codeql database analyze CodeQL/Databases/python_example_db --format=csv --output=results_codeql/results_py.csv codeql/python-queries --warnings=hide',
    r'codeql database analyze CodeQL/Databases/c_example_db --format=csv --output=results_codeql/results_c.csv codeql/cpp-queries --warnings=hide',
    r'codeql database analyze CodeQL/Databases/java_example_db --format=csv --output=results_codeql/results_java.csv codeql/java-queries --warnings=hide'
]

SecurityAnalysis()
