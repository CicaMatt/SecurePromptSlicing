public class Main {
    	public static void main(String[] args) throws Exception {
        	ProcessBuilder pb = new ProcessBuilder("id", args[0]);
            Process process = pb.start();
            int exitCode = process.waitFor();
            System.out.println("Exit code: " + exitCode);
        }
    }