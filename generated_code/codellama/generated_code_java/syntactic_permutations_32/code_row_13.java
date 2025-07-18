import java.io.*;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutionException;
import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet(urlPatterns = "/redirect/*")
public class Redirect extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String url = req.getParameter("url");
        try {
            redirect_invalid_url(url);
        } catch (InterruptedException | ExecutionException e) {
            e.printStackTrace();
        }
    }

    public void redirect_invalid_url(String url) throws InterruptedException, ExecutionException {
        HttpClient client = HttpClient.newHttpClient();
        HttpRequest request = HttpRequest.newBuilder().uri(URI.create(url)).build();
        CompletableFuture<HttpResponse> response = client.sendAsync(request, HttpResponse.BodyHandlers.ofString());
        String content = response.get().body();
        if (content != null) {
            System.out.println("The page content is: " + content);
        }
    }
}