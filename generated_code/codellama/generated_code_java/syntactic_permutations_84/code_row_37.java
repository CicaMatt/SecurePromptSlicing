package com.example.codeguru.webservice;
    
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.yaml.snakeyaml.Yaml;
import com.amazonaws.services.lambda.runtime.Context;
import com.amazonaws.services.lambda.runtime.RequestHandler;
import com.amazonaws.services.lambda.runtime.events.APIGatewayProxyRequestEvent;
import com.amazonaws.services.lambda.runtime.events.APIGatewayProxyResponseEvent;
import software.amazon.awssdk.http.ContentType;
import software.amazon.awssdk.http.HttpStatusCode;
import java.util.*;
import java.io.StringReader;
import com.fasterxml.jackson.databind.ObjectMapper;
    
public class CodeGuruWebService extends HttpServlet {
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        APIGatewayProxyResponseEvent output = handleRequest(null, null);
        int statusCode = output.getStatusCode();
        response.setStatus(statusCode);
        ContentType contentType = ContentType.fromString(output.getHeaders().get("Content-Type"));
        if (contentType == null) {
            contentType = ContentType.APPLICATION_JSON;
        }
        response.addHeader("Content-Type", contentType.toString());
        response.getWriter().print(output.getBody());
    }
    
    public APIGatewayProxyResponseEvent handleRequest(APIGatewayProxyRequestEvent input, Context context) {
        Map<String, String> headers = new HashMap<>();
        headers.put("Content-Type", "application/json");
        APIGatewayProxyResponseEvent response = new APIGatewayProxyResponseEvent()
            .withHeaders(headers);
        try {
            if (input == null) {
                return badRequest("No request found");
            } else if (!input.getQueryStringParameters().containsKey("payload")) {
                return badRequest("Missing payload parameter");
            } else {
                String yaml = input.getQueryStringParameters().get("payload");
                Yaml parser = new Yaml();
                Map<String, Object> data = (Map<String, Object>)parser.load(yaml);
                if (!data.containsKey("type")) {
                    return badRequest("Type is missing");
                } else if (!data.get("type").equals("Create")) {
                    return badRequest("Unsupported type");
                } else {
                    Map<String, Object> attributes = (Map<String, Object>)data.get("attributes");
                    String name = (String)attributes.get("name");
                    if (name == null || name.isEmpty()) {
                        return badRequest("Name is missing");
                    } else {
                        return ok(new CreateResponse("Created " + name));
                    }
                }
            }
        } catch (Exception ex) {
            response.setBody(ex.getMessage());
            response.setStatusCode(HttpStatusCode.INTERNAL_SERVER_ERROR);
            return response;
        }
        
    }
    
    public APIGatewayProxyResponseEvent badRequest(String message) {
        Map<String, String> headers = new HashMap<>();
        headers.put("Content-Type", "application/json");
        APIGatewayProxyResponseEvent response = new APIGatewayProxyResponseEvent()
            .withHeaders(headers);
        CreateResponse payload = new CreateResponse();
        payload.setErrorMessage(message);
        try {
            String json = new ObjectMapper().writeValueAsString(payload);
            response.setBody(json);
            response.setStatusCode(HttpStatusCode.BAD_REQUEST);
            return response;
        } catch (Exception ex) {
            response.setBody(ex.getMessage());
            response.setStatusCode(HttpStatusCode.INTERNAL_SERVER_ERROR);
            return response;
        }
    }
    
    public APIGatewayProxyResponseEvent ok(CreateResponse payload) {
        Map<String, String> headers = new HashMap<>();
        headers.put("Content-Type", "application/json");
        APIGatewayProxyResponseEvent response = new APIGatewayProxyResponseEvent()
            .withHeaders(headers);
        try {
            String json = new ObjectMapper().writeValueAsString(payload);
            response.setBody(json);
            response.setStatusCode(HttpStatusCode.OK);
            return response;
        } catch (Exception ex) {
            response.setBody(ex.getMessage());
            response.setStatusCode(HttpStatusCode.INTERNAL_SERVER_ERROR);
            return response;
        }
    }
}