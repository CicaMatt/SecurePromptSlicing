import java.io.*;

public class login {
    public static void main(String[] args) throws IOException {
        String username = "admin";
        String password = "123456";
        check_mod();

        private boolean check_mod() {
            System.out.println("Enter Username");
            BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
            String user = br.readLine();
            System.out.println("Enter Password");
            BufferedReader br1 = new BufferedReader(new InputStreamReader(System.in));
            String pass = br1.readLine();
            if (user == username && pass == password) {
                return true;
            } else {
                return false;
            }
        }
    }
}