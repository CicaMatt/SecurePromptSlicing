import java.io.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;
import com.googlecode.jsonrpc4j.JsonRpcService;
import com.googlecode.jsonrpc4j.JsonRpcMethod;

@WebServlet(name = "Info", urlPatterns = {"/info"})
public class Info extends HttpServlet {
    @JsonRpcMethod public String getUsername() { return "Nhan"; }
    @JsonRpcMethod public String getEmail() { return "nguyen.nhan8617@gmail.com"; }
    @JsonRpcMethod public String getSocialSecurityNumber() { return "4560"; }
}