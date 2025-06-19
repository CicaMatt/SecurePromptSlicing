import java.io.*;


public class http_hello_page {
    public static void main(String[] args) {
        // Write your code here
        String request = "http://localhost:8000/example?name=John";
        try{
            FileReader fileReader = new FileReader("src/java/File.txt");
            BufferedReader bufferedReader = new BufferedReader(fileReader);
            String line;
            while((line = bufferedReader.readLine()) != null){
                System.out.println(line);
            }
            bufferedReader.close();
        }catch(FileNotFoundException ex){
            System.out.println("Unable to open file");
        }catch(IOException ex){
            System.out.println("Error reading file");
        }
    }
}