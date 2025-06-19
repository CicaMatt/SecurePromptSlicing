package com.makotojava.learn.hellojunit5;

import static org.hamcrest.CoreMatchers.*;
import static org.hamcrest.MatcherAssert.*;

import java.util.regex.Pattern;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.server.handler.AbstractHandler;
import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Nested;
import org.junit.jupiter.api.Test;
import org.junit.platform.runner.JUnitPlatform;
import org.junit.runner.RunWith;

@RunWith(JUnitPlatform.class)
public class RedirectHandlerTest {

  private static Server server = null;
  
  @BeforeAll
  public static void setUp() throws Exception {
    System.out.println("In setUp()...");
    int port = getPort();
    server = new Server(port);
    server.setHandler(new RedirectHandler());
    server.start();
  }
  
  @AfterAll
  public static void tearDown() throws Exception {
    System.out.println("In tearDown()...");
    if (server != null && !server.isStopped()) {
      server.stop();
    }
  }
  
  private static int getPort() {
    return Integer.parseInt(System.getProperty("jetty.port", "8080"));
  }
  
  @Test
  public void testRedirectToExampleDotCom() throws Exception {
    System.out.println("In testRedirectToExampleDotCom()...");
    assertThat(getUrlContent("/?target=http://example.com"), containsString("Example Domain"));
  }
  
  @Test
  public void testRedirectToRootWhenTargetDoesNotMatchRegex() throws Exception {
    System.out.println("In testRedirectToRootWhenTargetDoesNotMatchRegex()...");
    assertThat(getUrlContent("/?target=http://www.google.com"), containsString("<title>Error 404 - Not Found</title>"));
  }
  
  @Test
  public void testRedirectToRootWhenTargetIsBlank() throws Exception {
    System.out.println("In testRedirectToRootWhenTargetIsBlank()...");
    assertThat(getUrlContent("/?target="), containsString("<title>Error 404 - Not Found</title>"));
  }
  
  @Test
  public void testRedirectToRootWhenTargetIsMissing() throws Exception {
    System.out.println("In testRedirectToRootWhenTargetIsMissing()...");
    assertThat(getUrlContent("/"), containsString("<title>Error 404 - Not Found</title>"));
  }
  
  private String getUrlContent(String path) throws Exception {
    
    StringBuilder url = new StringBuilder();
    url.append("http://localhost:");
    url.append(getPort());
    url.append(path);
    
    System.out.println("Getting content at URL: " + url.toString());
    
    String line;
    StringBuilder content = new StringBuilder();
    try (java.util.Scanner scanner = new java.util.Scanner(new java.net.URL(url.toString()).openStream())) {
      while (scanner.hasNextLine()) {
        line = scanner.nextLine();
        content.append(line).append("\n");
      }
    }
    
    return content.toString();
  }
  
  private static class RedirectHandler extends AbstractHandler {

    @Override
    public void handle(String target, Request baseRequest, HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
      // Get the "target" parameter
      String targetUrl = request.getParameter("target");
      System.out.println("Target URL: '" + targetUrl + "'");
      if (isValidRedirect(targetUrl)) {
        // Redirect to it
        response.setContentType("text/html;charset=utf-8");
        response.setStatus(HttpServletResponse.SC_MOVED_TEMPORARILY);
        System.out.println("Redirecting...");
        response.sendRedirect(targetUrl);
      } else {
        // Redirect to the root page
        response.setContentType("text/html;charset=utf-8");
        response.setStatus(HttpServletResponse.SC_MOVED_TEMPORARILY);
        System.out.println("Redirecting to /...");
        response.sendRedirect("/");
      }
    }
    
    private boolean isValidRedirect(String targetUrl) {
      // Does the URL contain "example.com"?
      Pattern pattern = Pattern.compile(".+example\\.com.*", Pattern.CASE_INSENSITIVE);
      return pattern.matcher(targetUrl).matches();
    }
  }
}