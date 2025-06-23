public class Main {
        public static void main(String[] args) {
            String username = args[0];
            ProcessBuilder pb = new ProcessBuilder("id", username);
            try {
                Process process = pb.start();
                int exitStatus = process.waitFor();
                System.out.println(exitStatus);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }