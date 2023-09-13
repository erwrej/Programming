package com.rustam.mobile_phone_payment.utils;

import com.rustam.mobile_phone_payment.dto.BalancePhoneDto;
import com.rustam.mobile_phone_payment.services.BalancePhoneService;
import lombok.RequiredArgsConstructor;
import org.springframework.boot.CommandLineRunner;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.Arrays;

@Service
@RequiredArgsConstructor
public class InitiateUtils implements CommandLineRunner {

    private final BalancePhoneService balancePhoneService;

    @Override
    public void run(String... args) throws Exception {
        balancePhoneService.saveAll(
                new ArrayList<BalancePhoneDto>(
                        Arrays.asList(
                                new BalancePhoneDto(
                                        1,
                                        555000,
                                        "Иван",
                                        100
                                ),
                                new BalancePhoneDto(
                                        2,
                                        444000,
                                        "Марья",
                                        250
                                ),
                                new BalancePhoneDto(
                                        3,
                                        111000,
                                        "Иван",
                                        60
                                )
                        )
                )
        );
        
    }
}
