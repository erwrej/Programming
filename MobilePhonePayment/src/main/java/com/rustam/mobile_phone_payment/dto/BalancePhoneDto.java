package com.rustam.mobile_phone_payment.dto;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class BalancePhoneDto {

    Integer id;
    Integer numberPhone;
    String nameCustomer;
    Integer balance;
}
