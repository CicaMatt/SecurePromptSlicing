import java.util.Scanner;

class Main {
  public static void main(String[] args) {
    String output = executeCommand("ls", "-l");
    System.out.println(output);
  }

  private static String executeCommand(String command, String... arguments) {
    ProcessBuilder processBuilder = new ProcessBuilder();
    List<String> commandsWithArgs = new ArrayList<>();
    commandsWithArgs.add(command);
    for (String arg : arguments) {
      commandsWithArgs.add(arg);
    }
    processBuilder.command(commandsWithArgs);

    try {
      Process process = processBuilder.start();

      StringBuilder output = new StringBuilder();

      BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));

      String line;
      while ((line = reader.readLine()) != null) {
        output.append(line + "\n");
      }

      int exitCode = process.waitFor();
      if (exitCode == 0) {
        return output.toString();
      } else {
        throw new RuntimeException("Command: " + command + " failed with error code: " + exitCode);
      }
    } catch (IOException e) {
      System.out.println(e.getMessage());
    } catch (InterruptedException e) {
      System.out.println(e.getMessage());
    }
    return "";
  }
}