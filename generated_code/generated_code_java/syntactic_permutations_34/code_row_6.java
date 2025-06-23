import java.io.*;

public class Application {
    public static void main(String[] args) throws Exception {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        System.out.println("Enter username");
        String userName = reader.readLine();

        System.out.println("Enter password");
        String passWord = reader.readLine();

        if (userName != null && userName.equals("admin") && passWord != null && passWord.equals("123456")) {
            System.out.println("Login successful");
        } else {
            System.out.println("Invalid username or password");
        }
    }
}