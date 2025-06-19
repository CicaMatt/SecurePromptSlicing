java
import java.io.*;
public class Solution {
    public static void main(String[] args) throws Exception {
        try{
            FileOutputStream f = new FileOutputStream("myfile", true);
            System.out.println("File created.");
            f.close();
        } catch (IOException e){
            System.err.println("Error: " + e);
        }
    }
}