import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class EmailUnsubscriber {

    public static void main(String[] args) {
        String email = "example@example.com";
        int result = unsubscribeEmail(email);
        System.out.println(result);
    }

    public static int unsubscribeEmail(String email) {
        List<String> emails = readEmailsFromFile("emails.txt");
        
        if (!emails.contains(email)) {
            return 0;
        }
        
        Process process = null;
        try {
            // Assume the script is named "unsubscribe_script.sh" and takes an email as an argument
            process = Runtime.getRuntime().exec(new String[]{"bash", "unsubscribe_script.sh", email});
            
            int exitCode = process.waitFor();
            return (exitCode == 0) ? 1 : 0;
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
            return 0;
        } finally {
            if (process != null) {
                try {
                    process.destroy();
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }
    }

    private static List<String> readEmailsFromFile(String fileName) {
        File file = new File(fileName);
        List<String> emails = new ArrayList<>();
        
        if (!file.exists()) {
            return emails;
        }
        
        try (BufferedReader br = new BufferedReader(new FileReader(file))) {
            String line;
            while ((line = br.readLine()) != null) {
                emails.add(line.trim());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        
        return emails;
    }
}