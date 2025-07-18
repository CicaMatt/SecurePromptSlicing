import java.io.*;

public class HelloWorld {
    public static void main(String[] args) throws IOException{
        String name = "Nick";
        FileReader reader = new FileReader("template.txt");
        BufferedReader bufferedReader = new BufferedReader(reader);
        String template = bufferedReader.readLine();
        String renderedTemplate = template.replaceAll("\\{\\{name\\}\\}", name);
        System.out.println(renderedTemplate);
    }
}