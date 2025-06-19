import java.io.*;
class ExecuteLS{ 
    public static void main(String args[]) throws Exception{
        String command = "ls";
        Process p= Runtime.getRuntime().exec(command); 
        BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String line;
        while ((line = reader.readLine()) != null) {
            System.out.println(line);
        }
        p.waitFor();
    }
}