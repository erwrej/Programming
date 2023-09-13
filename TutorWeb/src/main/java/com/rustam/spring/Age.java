package com.rustam.spring;

public enum Age {
    UNIVERSITY_STUDENT("University student"), YOUNG("Young"),
    MIDDLE("Middle"), OLD("Old"), ANY("Any");

    private String displayValue;

    private Age(String displayValue) {
        this.displayValue = displayValue;
    }

    public String getDisplayValue() {
        return displayValue;
    }

}
