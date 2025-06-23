import java.io.*;
class Main{
    public static void main(String[] args)throws IOException{
        int size = 1024;
        char buf[]=new char[size];
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        System.out.print("Enter the input: ");
        String input = br.readLine();
        int len = input.length();
        for(int i=0;i<len;i++){
            buf[i]=input.charAt(i);
        }
    }
}