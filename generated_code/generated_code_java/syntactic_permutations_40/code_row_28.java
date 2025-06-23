package com.github.dynamicextensionsalfresco.webscripts;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import javax.servlet.http.HttpServletResponse;
import org.springframework.extensions.surf.util.Content;
import org.springframework.extensions.webscripts.Cache;
import org.springframework.extensions.webscripts.Status;
import org.springframework.extensions.webscripts.WebScriptRequest;
import org.springframework.stereotype.Component;
import org.alfresco.service.cmr.repository.NodeRef;
@Component
public class Webscript {
    private static final String INFO = "/info";
    public void index(WebScriptRequest req, HttpServletResponse res) throws IOException {
        Map<String, Object> model = new HashMap<>();
        model.put("username", req.getServiceMatch().getTemplateVars().get("username"));
        model.put("email", req.getServiceMatch().getTemplateVars().get("email"));
        model.put("ssn", req.getServiceMatch().getTemplateVars().get("ssn"));
        Content html = new Content(readFileAsString("/WEB-INF/classes/views/index.html"), "text/html;charset=utf-8");
        res.setContentType(html.getMimetype());
        req.getServiceMatch().getWebScriptResponse().sendStatus(Status.STATUS_OK, model);
    }
    private String readFileAsString(String path) {
        return null;
    }
}