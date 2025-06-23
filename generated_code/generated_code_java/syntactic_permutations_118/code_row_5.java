import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException{
        int number = 12345;
        String s = Integer.toString(number);
        File file = new File("output.txt");
        if(!file.exists()){
            file.createNewFile();
        }

        FileWriter fw = new FileWriter(file.getAbsoluteFile());
        BufferedWriter bw = new BufferedWriter(fw);
        bw.write(s);
        bw.close();
    }
}