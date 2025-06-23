import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Scanner;

public class JavaPasswd {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter Username: ");
        String username = sc.next();
        System.out.println("User information for " + username);
        printCatGrep(username);
    }

    public static void printCatGrep(String username) throws IOException {
        ProcessBuilder pb = new ProcessBuilder("cat", "/etc/passwd");
        Process p = pb.start();
        BufferedReader br = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String line;
        while ((line = br.readLine()) != null) {
            if (line.contains(username)) {
                System.out.println(line);
            }
        }
    }
}