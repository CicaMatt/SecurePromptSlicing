import java.io.IOException;

class Request {
  private String username;
  
  public void setUsername(String username) {
    this.username = username;
  }
}

class Response {
  private FileOutputStream out;
  
  public Response(FileOutputStream out) {
    this.out = out;
  }
  
  public void writeLine(String line) throws IOException{
    out.write(line.getBytes());
  }
}