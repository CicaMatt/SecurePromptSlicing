import java.io.*;
    
    public class HelloWorld {
    
        private static String http_hello_page(FileInputStream request, FileOutputStream response) throws IOException{
            //read username from request
            BufferedReader br = new BufferedReader(new InputStreamReader(request));
            String username = "";
            
            while (true){
                String line = br.readLine();
                
                if(line == null || line.equals("")){
                    break;
                }
                
                int start_index = line.indexOf("<input name=\"username\" value=\"") + 28;
                int end_index = line.indexOf("\"/>");
                
                username = line.substring(start_index, end_index);
            }
            
            br.close();
    
            //write response to the file stream
            BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(response));
            
            String http_header = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n";
    
            String html_content = "<!DOCTYPE html>\n" +
                "<html><body>Hello " + username + "</body></html>";
            
            bw.write(http_header);
            bw.write(html_content);
            bw.close();
    
            return "";
        }
    }