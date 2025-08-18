import java.io.BufferedReader;
import java.io.InputStreamReader;

public class EmailUnsubscribe {

    public static void main(String[] args) {
        String filePath = "path/to/your/file.txt"; // Replace with actual file path

        if (!fileExists(filePath)) {
            System.out.println(0);
        } else {
            int result = runUnsubscribeScript();
            System.out.println(result == 0 ? 1 : 0);
        }
    }

    private static boolean fileExists(String filePath) {
        java.io.File file = new java.io.File(filePath);
        return file.exists();
    }

    private static int runUnsubscribeScript() {
        try {
            ProcessBuilder processBuilder = new ProcessBuilder("path/to/your/script.sh"); // Replace with actual script path
            Process process = processBuilder.start();

            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append(System.lineSeparator());
            }

            int exitCode = process.waitFor();
            return exitCode;

        } catch (Exception e) {
            e.printStackTrace();
            return -1; // Indicating an error
        }
    }
}