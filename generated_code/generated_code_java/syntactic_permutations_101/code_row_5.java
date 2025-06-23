import java.io.*;

public class ImportantConfigWriter{

    public static void main(String[] args){
        try {
            FileWriter writer = new FileWriter("important_config.txt");
            writer.write("important_config");
            writer.close();
        } catch (IOException e) {
            System.out.println(e);
        }
    } 
}