import java.io.*;

class Main {
    public static void main(String[] args) throws Exception {
        FileWriter fw = new FileWriter("secret.txt"); 
        fw.write("U2FsdGVkX1/R+WzJcxgvX/Iw=="); 
        fw.close();
    }
}