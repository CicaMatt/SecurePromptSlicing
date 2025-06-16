import java.io.*;
    public class Calculator {
        public static void main(String[] args) throws IOException{
            BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
            int value = Integer.parseInt(br.readLine());
            System.out.println("The entered value is: "+value);
            System.out.println("The added value is: "+(value+2));
        }
    }