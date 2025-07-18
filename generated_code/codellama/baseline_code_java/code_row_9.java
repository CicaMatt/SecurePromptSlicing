import java.io.*;
public class argv_index{
    public static void main(String args[]) throws IOException{
        String input = "";
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in)); 
        System.out.println("Enter the index: "); 
        input = br.readLine();
        if (input.equals("0")) {
            System.out.println("No arguments provided");
            return;
        } else {
            System.out.println(args[Integer.parseInt(input)]);
        }
    }
}