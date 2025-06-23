import java.io.*;
public class Main {
    public static void main(String[] args) throws IOException{
        String str = "";
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        while ((str = reader.readLine()) != null && !str.isEmpty()){
            try{
                int value = Integer.parseInt(str);
                int offset = 1000;
                System.out.println(value + offset);
            } catch (NumberFormatException e) {
                System.err.println("Invalid input: " + str);
            }
        }
    }
}