package com.rustam.spring.controllers;

import java.util.List;

import javax.validation.Valid;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.RequestMapping;

import com.rustam.spring.dao.OrderDAO;
import com.rustam.spring.models.Order;

import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PatchMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;

@Controller
@RequestMapping("/orders")
public class OrderController {
    OrderDAO orderDAO;

    @Autowired
    public OrderController(OrderDAO orderDAO) {
        this.orderDAO = orderDAO;
    }

    @GetMapping("/index/{userId}")
    public String index(@PathVariable("userId") int userId, Model model) {
        model.addAttribute("orderList", orderDAO.getOrdersByUserId(userId));
        return "orders/index";
    }

    @GetMapping("/{id}/show")
    public String show(@PathVariable("id") int id, Model model) {
        Order order = orderDAO.getById(id);
        model.addAttribute("order", order);
        return "orders/show";
    }

    @GetMapping("/{id}/edit")
    public String edit(@PathVariable("id") int id, Model model) {
        model.addAttribute("order", orderDAO.getById(id));
        return "orders/edit";
    }

    @PatchMapping("/{id}/edit")
    public String update(@ModelAttribute("order") @Valid Order order, @PathVariable("id") int id) {
        orderDAO.updateById(id, order);
        return "redirect:/orders/{id}";
    }

    @DeleteMapping("/{id}")
    public String delete(@ModelAttribute("order") Order order, @PathVariable("id") int id) {
        orderDAO.deleteById(id);
        return "redirect:/orders/index/" + order.getStudentId();
    }

    @GetMapping("/new/{userId}")
    public String create(@PathVariable("userId") Integer userId, Model model) {
        Order order = new Order();
        order.setStudentId(userId);
        model.addAttribute("order", order);
        return "orders/create";
    }

    @PostMapping("/new")
    public String createOrder(@ModelAttribute("order") Order order) {
        orderDAO.save(order);
        return "redirect:/orders/index/" + order.getStudentId();
    }
}
