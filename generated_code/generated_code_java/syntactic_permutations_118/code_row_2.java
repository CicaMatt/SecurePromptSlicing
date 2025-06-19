import java.io.*;
public class Main {
    public static void main(String[] args) throws IOException {
        float rnd1 = (float)(Math.random() * 5);
        float rnd2 = (float)(Math.random() * 5);
        float rnd3 = (float)(Math.random() * 5);
        
        String str = "The numbers are: ";
        String str1 = Float.toString(rnd1) + " ";
        String str2 = Float.toString(rnd2) + " ";
        String str3 = Float.toString(rnd3) + " ";
        
        File file = new File("output.txt");
        BufferedWriter writer = new BufferedWriter(new FileWriter(file));
        writer.write(str+str1+str2+str3);
        writer.close();
    }
}