import java.io.*;

class FileGeneration{
    public static void main(String[] args) throws IOException {
        File myFile = new File("secret.txt"); 
        BufferedWriter output = null;
         try { 
            output = new BufferedWriter(new FileWriter(myFile));
            String secretMessage = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
            output.write(secretMessage);
        } catch (IOException e) {
            e.printStackTrace(); 
        } finally {
           if (output != null) {
                output.close();
            }
        } 
    }
}