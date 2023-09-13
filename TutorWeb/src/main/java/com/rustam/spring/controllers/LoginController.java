package com.rustam.spring.controllers;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;

import com.rustam.spring.dao.UserDAO;
import com.rustam.spring.models.Login;
import com.rustam.spring.models.User;

@Controller
@RequestMapping("/login")
public class LoginController {
    private UserDAO userDAO;
    private final Integer USER_NOT_FOUND = -1;

    public LoginController(UserDAO userDAO) {
        this.userDAO = userDAO;
    }

    @GetMapping("")
    public String loginPage() {
        return "loginPages/login";
    }

    @GetMapping("/auth")
    public String auth(@RequestParam("failed") String failed, Model model) {
        model.addAttribute("login", new Login());
        if (!failed.equals("true")) {
            failed = "";
            model.addAttribute("failed", failed);
            return "loginPages/auth";
        } else {
            failed = "Incorrect login or password!";
            model.addAttribute("failed", failed);
            return "loginPages/auth";
        }
    }

    @PostMapping()
    public String verification(@ModelAttribute("login") Login login) {
        Object result = userDAO.findUserWithLoginAndPasswordAndReturnId(login);
        if (result.equals(USER_NOT_FOUND)) {
            return "redirect:/login/auth?failed=true";
        } else {
            return "redirect:/users/" + result;
        }

    }

    @GetMapping("/register")
    public String register(@RequestParam("failed") String failed, Model model) {
        model.addAttribute("user", new User());
        if (!failed.equals("true")) {
            failed = "";
            model.addAttribute("failed", failed);
            return "loginPages/registration";
        } else {
            failed = "Login, Email and phone must be unique!";
            model.addAttribute("failed", failed);
            return "loginPages/registration";
        }
    }

    @PostMapping("/register")
    public String createUser(@ModelAttribute("user") User user) {
        if (user.getStatus() == null) {
            user.setStatus("student");
        } else {
            user.setStatus("tutor");
        }
        if (!userDAO.isAlreadySaved(user)) {
            userDAO.save(user);
        } else {
            return "redirect:/login/register?failed=true";
        }
        if (user.getStatus().equals("tutor")) {
            return "redirect:/users/" + user.getId() + "/questionnaire/edit";
        } else {
            return "redirect:/orders/index/" + user.getId();
        }
    }
}
