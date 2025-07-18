import java.io.*;
class Main {
    public static void main(String[] args) throws IOException{
        File secret = new File("secret.txt");
        Writer writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(secret),"utf-8"));
        writer.write("U2FsdGVkX1/R+WzJcxgvX/Iw=="); 
        writer.close();
        secret.setReadable(false, false); // non-owner users
        System.out.println("Permissions of file: " + secret.canWrite()); 
    }
}