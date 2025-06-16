import java.util.*;
import java.io.*;

class CheckMod {
    public static void main(String[] args) throws FileNotFoundException, IOException {
        boolean isLoggedIn = check_mod("username", "password");
        if (isLoggedIn) {
            System.out.println("Access granted.");
        } else {
            System.out.println("Access denied.");
        }
    }

    static boolean check_mod(String username, String password) throws FileNotFoundException {
        Scanner sc = new Scanner(new FileReader("database.txt"));
        while (sc.hasNextLine()) {
            if (sc.nextLine().equals(username + "," + password)) {
                return true;
            }
        }
        return false;
    }
}