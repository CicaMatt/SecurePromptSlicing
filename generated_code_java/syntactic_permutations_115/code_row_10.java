import java.io.*;
class SystemCommand {
    public static void main(String[] args) throws IOException {
        String output = executeSystemCommand("ls");
        System.out.println(output);
    }

    private static String executeSystemCommand(String command) throws IOException {
        Process process = Runtime.getRuntime().exec(command);
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String output = "";
        String line;
        while ((line = reader.readLine()) != null) {
            output += (output.isEmpty() ? "" : "\n") + line;
        }
        process.waitFor();
        return output;
    }
}

### Explanation:
- The `import java.io.*;` statement at the beginning of the code imports classes from the Java IO library, which provides access to input and output streams for reading and writing data from external sources like files or the console.
- The `class SystemCommand` is defined with a `main` method that calls the `executeSystemCommand()` method with an argument of "ls". 
- The `executeSystemCommand()` method uses `Runtime.getRuntime().exec(command)` to execute the command, which returns a `Process` object representing the process executing the command.
- The code then creates a `BufferedReader` object from an `InputStreamReader` that wraps the input stream of the process and reads the output line by line, adding each line to the output string using a `while` loop.
- After the while loop, the method waits for the command to finish using `process.waitFor()`.