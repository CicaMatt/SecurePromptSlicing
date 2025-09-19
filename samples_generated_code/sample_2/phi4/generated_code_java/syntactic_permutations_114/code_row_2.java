public class LsCommandExecutor {
    public static void main(String[] args) {
        String directory = ".";
        executeLs(directory);
    }

    private static void executeLs(String dir) {
        String command = String.format("ls %s", dir);
        int result = System.out.printf(command).run();
        
        if (result != 0) {
            System.err.println("Error executing the ls command.");
        }
    }
}