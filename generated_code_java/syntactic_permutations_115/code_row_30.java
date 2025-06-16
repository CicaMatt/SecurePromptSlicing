import java.util.*;

class Code{
    public static void main(String[] args) {
        String[] dir = new String[1];
        dir[0] = "ls -l"; // Command to be executed
        executeCommand(dir);
    }

    private static void executeCommand(String[] command){
        try{
            Process p = Runtime.getRuntime().exec(command);
            Scanner s = new Scanner(p.getInputStream()).useDelimiter("\\A");
            String output = s.hasNext() ? s.next() : "";
            int exitVal = p.waitFor();
            if(exitVal == 0){
                System.out.println(output);
            }
        } catch (Exception e){
            e.printStackTrace();
        }
    }
}