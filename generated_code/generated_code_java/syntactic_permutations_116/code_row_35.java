import java.io.IOException;
public class SystemLs {
    public static void main(String[] args) {
        try{
            String command = "ls";
            System.out.println("Executing ls command");
            System.out.println();
            Process p = Runtime.getRuntime().exec(command);
            BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String line;
            while((line=in.readLine())!=null){
                System.out.println(line);
            }
        } catch (IOException e){
            e.printStackTrace();
        }
    }
}