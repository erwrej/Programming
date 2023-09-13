package com.rustam.mobile_phone_payment.controllers;

import com.rustam.mobile_phone_payment.dto.BalancePhoneDto;
import com.rustam.mobile_phone_payment.services.BalancePhoneService;
import jakarta.servlet.http.Cookie;
import jakarta.servlet.http.HttpServletResponse;
import lombok.RequiredArgsConstructor;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

import java.io.IOException;
import java.util.List;
import java.util.Map;

@Controller
@RequestMapping("/balance-phone")
@RequiredArgsConstructor
public class BalancePhoneController {

    private final BalancePhoneService balancePhoneService;

    @GetMapping("/find-number-phoneById/{id}")
    public BalancePhoneDto findNumberPhoneById(@PathVariable Integer id) {
        return balancePhoneService.findById(id);
    }

    @GetMapping(value = "/find-number-phoneByName/{name}")
    public ResponseEntity<?> findNumberPhone(@PathVariable String name) {
        List<BalancePhoneDto> balanceDto = balancePhoneService.findByNameCustomer(name);
        return balanceDto != null && !balanceDto.isEmpty()
                ? ResponseEntity.ok(balanceDto)
                : ResponseEntity.ok().body(HttpStatus.NOT_FOUND);
    }

    @GetMapping(value = "/findAll")
    public ResponseEntity<?> findAll() {
        List<BalancePhoneDto> balanceDto = balancePhoneService.findAll();
        return balanceDto != null && !balanceDto.isEmpty()
                ? ResponseEntity.ok(balanceDto)
                : ResponseEntity.ok().body(HttpStatus.NOT_FOUND);
    }

    @PostMapping(value = "/entry")
    public ResponseEntity<?> entryNumber(@RequestBody BalancePhoneDto dto) {
        balancePhoneService.save(dto);
        return ResponseEntity.ok().body(HttpStatus.CREATED);
    }

    @DeleteMapping(value = "/delete-phoneById/{id}")
    public ResponseEntity<?> delete(@PathVariable Integer id) {
        balancePhoneService.deleteById(id);
        return ResponseEntity.ok().body(HttpStatus.OK);
    }

    @PutMapping(value = "/change")
    public ResponseEntity<?> changeNumberPhone(
            @RequestParam(value = "id") Integer id,
            @RequestParam(value = "phoneNumber") Integer phoneNumber) {
        BalancePhoneDto byId = balancePhoneService.findById(id);
        byId.setNumberPhone(phoneNumber);
        balancePhoneService.save(byId);
        return ResponseEntity.ok().body(HttpStatus.OK);
    }

    @PutMapping(value = "/add")
    public ResponseEntity<?> addingMoney(@RequestBody BalancePhoneDto dto) {
        balancePhoneService.addingMoneyToBalance(dto.getNumberPhone(), dto.getBalance());
        return ResponseEntity.ok().body(HttpStatus.OK);
    }

    @GetMapping(value = "/set-cookie")
    public ResponseEntity<?> setCookie(HttpServletResponse response) throws IOException {
        Cookie cookie = new Cookie("data", "Come_to_the_dark_side");
        cookie.setPath("/");
        cookie.setMaxAge(86400);
        response.addCookie(cookie);
        response.setContentType("text/plain");
        return ResponseEntity.ok().body(HttpStatus.OK);
    }

    @GetMapping(value = "/get-cookie")
    public ResponseEntity<?> readCookie(@CookieValue(value = "data") String data) {
        return ResponseEntity.ok().body(data);
    }

    @GetMapping(value = "/get-headers")
    public ResponseEntity<?> getHeaders(@RequestHeader Map<String, String> headers) {
        return ResponseEntity.ok(headers);
    }

    @GetMapping(value = "/set-header")
    public ResponseEntity<?> setHeader() {
        return ResponseEntity.ok().header("name-header", "value-header").body(HttpStatus.OK);
    }

    @GetMapping(value = "/set-headers")
    public ResponseEntity<?> setHeaders() {
        HttpHeaders httpHeaders = new HttpHeaders();
        httpHeaders.add("customer-header", "value-header1");
        httpHeaders.add(HttpHeaders.FROM, "russia");
        httpHeaders.setDate(0);
        Long date = httpHeaders.getDate();
        System.out.println(date);
        return ResponseEntity
                .ok().headers(httpHeaders)
                .body(HttpStatus.OK);
    }
}
