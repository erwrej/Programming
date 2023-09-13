package com.rustam.mobile_phone_payment.mappers;

import com.rustam.mobile_phone_payment.dto.BalancePhoneDto;
import com.rustam.mobile_phone_payment.entities.BalancePhoneEntity;
import lombok.RequiredArgsConstructor;
import org.modelmapper.ModelMapper;
import org.springframework.stereotype.Service;

@Service
@RequiredArgsConstructor
public class BalancePhoneMapper {

    public final ModelMapper modelMapper;

    public BalancePhoneDto mapToBalancePhoneDto(BalancePhoneEntity entity) {
        return modelMapper.map(entity, BalancePhoneDto.class);
    }

    public BalancePhoneEntity mapToBalancePhoneEntity(BalancePhoneDto dto) {
        return modelMapper.map(dto, BalancePhoneEntity.class);
    }
}
