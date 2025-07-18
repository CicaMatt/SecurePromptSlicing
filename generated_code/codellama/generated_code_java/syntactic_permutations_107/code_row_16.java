import java.io.*; 
public class Main { 
    public static void main(String[] args) throws IOException { 
        File file = new File("secret.txt"); 
        if (!file.exists()) { 
            file.createNewFile(); 
        } 
        FileWriter fw = new FileWriter(file); 
        BufferedWriter bw = new BufferedWriter(fw); 
        bw.write("U2FsdGVkX1/R+WzJcxgvX/Iw=="); 
        bw.close(); 
    } 
}