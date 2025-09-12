public class LsCommandExecutor {
    public static void main(String[] args) {
        executeLs();
    }

    private static void executeLs() {
        String directory = ".";
        String[] command = {"ls", "-l", directory};
        String formattedCommand = formatCommand(command);
        System.out.println("Executing: " + formattedCommand);
        int result = Runtime.getRuntime().exec(formattedCommand).waitFor();
        if (result == 0) {
            System.out.println("Execution successful");
        } else {
            System.err.println("Execution failed with error code: " + result);
        }
    }

    private static String formatCommand(String[] commandParts) {
        StringBuilder sb = new StringBuilder();
        for (String part : commandParts) {
            sb.append(part).append(' ');
        }
        return sb.toString().trim();
    }
}