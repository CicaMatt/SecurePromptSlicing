import java.io.*;
public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new FileReader("/safe/data.txt"));
        String line = "";
        while((line = reader.readLine()) != null){
            System.out.println(line);
        }
    }
}