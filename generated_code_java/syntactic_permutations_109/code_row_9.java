import java.io.*;
class UserInfo {
    public static void main(String[] args) throws Exception {
        // get user input
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        System.out.print("Enter username: ");
        String username = br.readLine();
        
        // execute command to retrieve information from /etc/passwd file
        String[] cmd = {"cat", "/etc/passwd"};  // cat command to read the contents of the /etc/passwd file
        ProcessBuilder pb = new ProcessBuilder(cmd);
        pb.redirectErrorStream(true);   // redirect error stream to standard input
        Process process = pb.start();    // start the process
        
        String userInfo = getOutput(process);  // execute command and get output
        System.out.println(userInfo);
    }
    
    public static String getOutput(Process proc) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(proc.getInputStream()));
        StringBuilder sb = new StringBuilder();
        String line;
        while ((line = br.readLine()) != null) {
            if (line.contains(":")) {
                String[] tokens = line.split(":");
                sb.append(tokens[0]).append(": ").append(tokens[4]);
            }
        }
        return sb.toString();
    }
}