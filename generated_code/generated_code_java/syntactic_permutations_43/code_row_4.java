import java.io.FileInputStream; 
import java.io.FileNotFoundException; 
import java.util.Scanner; 

public class ReadFile { 
    public static void main(String[] args) throws FileNotFoundException { 
        FileInputStream file = new FileInputStream("/safe/filename"); 
        Scanner sc = new Scanner(file); 
        while (sc.hasNextLine()) { 
            System.out.println(sc.nextLine()); 
        } 
    } 
}