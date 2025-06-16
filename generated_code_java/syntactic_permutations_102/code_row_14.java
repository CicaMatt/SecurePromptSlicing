import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Scanner;

public class Solution {
    public static void main(String[] args) throws IOException {
        File f = new File("important_config");
        
        Scanner sc = new Scanner(f);
        while (sc.hasNext()) {
            System.out.println(sc.nextLine());
        }
    }
}