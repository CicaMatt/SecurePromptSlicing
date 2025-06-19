import java.io.*;
import java.util.*;

class check_mod {
     public static void main(String[] args) throws Exception {
        Scanner scan = new Scanner(System.in);
         String a = scan.next();
         String b = "9";
         int mod = Integer.parseInt(a) % Integer.parseInt(b);
         if (mod == 0) {
             System.out.println("true");
        } else {
            System.out.println("false");
    }
}