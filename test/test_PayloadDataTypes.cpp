#include <gtest/gtest.h>
#include "PayloadDataTypes.h"

namespace Rovi {
    namespace Homie {
        TEST(PayploadDataTypes, String) {
            // String types are limited to 268,435,456 characters
            // An empty string (“”) is a valid payload
            auto value = String{""};
            EXPECT_TRUE(value.validateValue(""));
            EXPECT_TRUE(value.validateValue("abc"));
        }

        TEST(PayploadDataTypes, Integer) {
            // Integer types are UTF-8 encoded string literal representations of 64-bit signed whole numbers
            // Integers range from -9,223,372,036,854,775,808 (-263) to 9,223,372,036,854,775,807 (263-1)
            // The payload may only contain whole numbers and the negation character “-”. No other characters including spaces (” “) are permitted
            // A string with just a negation sign (“-”) is not a valid payload
            // An empty string (“”) is not a valid payload
            auto value = Integer{0};

            EXPECT_TRUE(value.validateValue("123"));
            EXPECT_TRUE(value.validateValue("-123"));
            EXPECT_FALSE(value.validateValue("+123"));
            EXPECT_FALSE(value.validateValue("123-"));
            EXPECT_FALSE(value.validateValue("-123-"));
            EXPECT_FALSE(value.validateValue("123.456"));
            EXPECT_FALSE(value.validateValue("abc"));
            EXPECT_FALSE(value.validateValue("-"));
            EXPECT_FALSE(value.validateValue(""));
            EXPECT_FALSE(value.validateValue(" "));
            EXPECT_FALSE(value.validateValue("123 456"));
            EXPECT_FALSE(value.validateValue("123,456"));

            EXPECT_EQ(Integer{"123"}, Integer{123});
            EXPECT_EQ(Integer{"-123"}, Integer{-123});
            EXPECT_NE(Integer{"123"}, Integer{-123});
            EXPECT_NE(Integer{"123"}, Integer{456});

            EXPECT_EQ("123", Integer{123}.toString());
            EXPECT_EQ("-123", Integer{-123}.toString());

            auto successful = value.setValue("123");
            EXPECT_TRUE(successful);
            EXPECT_EQ(value.value(), 123);
            EXPECT_EQ(value.toString(), "123");
            EXPECT_TRUE(value.isValid());

            successful = value.setValue("456.123");
            EXPECT_FALSE(successful);
            EXPECT_EQ(value.value(), 123);              // Still the last valid value
            EXPECT_EQ(value.toString(), "123");
            EXPECT_TRUE(value.isValid());

            successful = value.setValue("567");
            EXPECT_TRUE(successful);
            EXPECT_EQ(value.value(), 567);
            EXPECT_EQ(value.toString(), "567");
            EXPECT_TRUE(value.isValid());

            successful = value.setValue(Integer{890});
            EXPECT_TRUE(successful);
            EXPECT_EQ(value.value(), 890);
            EXPECT_EQ(value.toString(), "890");
            EXPECT_TRUE(value.isValid());

            // TBD: How to resolve? Warning is generated by the compiler but how to force???
            // successful = value.setValue(Integer{123.456});
            // EXPECT_FALSE(successful);
            // EXPECT_EQ(value.value(), 890);              // Still the last valid value
            // EXPECT_EQ(value.toString(), "890");
            // EXPECT_TRUE(value.isValid());
        }

        TEST(PayploadDataTypes, Float) {
            // Float types are UTF-8 encoded string literal representations of 64-bit signed floating point numbers
            // Floats range from 2-1074 to (2-2-52)*21023
            // The payload may only contain whole numbers, the negation character “-”, the exponent character “e” or “E” and the decimal separator “.”, no other characters, including spaces (” “) are permitted
            // The dot character (“.”) is the decimal separator (used if necessary) and may only have a single instance present in the payload
            // Representations of numeric concepts such as “NaN” (Not a Number) and “Infinity” are not a valid payload
            // A string with just a negation sign (“-”) is not a valid payload
            // An empty string (“”) is not a valid payload
            auto value = Float{0};
            EXPECT_TRUE(value.validateValue("123"));
            EXPECT_TRUE(value.validateValue("-123"));
            EXPECT_TRUE(value.validateValue("123.456"));
            EXPECT_TRUE(value.validateValue("-123.456"));
            EXPECT_TRUE(value.validateValue(".456"));
            EXPECT_TRUE(value.validateValue("-.456"));
            EXPECT_FALSE(value.validateValue("123.456.789"));
            EXPECT_FALSE(value.validateValue("-123.456.789"));
            EXPECT_FALSE(value.validateValue(".456.789"));
            EXPECT_FALSE(value.validateValue("-.456.789"));
            EXPECT_TRUE(value.validateValue("2e8"));
            EXPECT_TRUE(value.validateValue("2E8"));
            EXPECT_FALSE(value.validateValue("E8"));
            EXPECT_FALSE(value.validateValue("-E8"));
            EXPECT_FALSE(value.validateValue("2f8"));
            EXPECT_FALSE(value.validateValue("NaN"));
            EXPECT_FALSE(value.validateValue("nan"));
            EXPECT_FALSE(value.validateValue("Infinity"));
            EXPECT_FALSE(value.validateValue("infinity"));
            EXPECT_FALSE(value.validateValue("Inf"));
            EXPECT_FALSE(value.validateValue("inf"));
            EXPECT_FALSE(value.validateValue("-"));
            EXPECT_FALSE(value.validateValue(""));
            EXPECT_FALSE(value.validateValue(" "));

            EXPECT_EQ(Float{"123"}, Float{123});
            EXPECT_EQ(Float{"123.456"}, Float{123.456});
            EXPECT_EQ(Float{"-123"}, Float{-123});
            EXPECT_EQ(Float{"-123.456"}, Float{-123.456});
            EXPECT_EQ(Float{".456"}, Float{.456});
            EXPECT_EQ(Float{"-.456"}, Float{-.456});

            EXPECT_EQ(Float{"2e8"}, Float{2e8});
            EXPECT_EQ(Float{"2E8"}, Float{2E8});
            EXPECT_EQ(Float{"2E8"}, Float{2E+8});
            EXPECT_EQ(Float{"2E8"}, Float{2E+008});
            EXPECT_EQ(Float{"-2E8"}, Float{-2E8});
            EXPECT_EQ(Float{"2E-8"}, Float{2E-8});
            EXPECT_EQ(Float{"2E-8"}, Float{2E-008});
            EXPECT_EQ(Float{"-2E-8"}, Float{-2E-8});
            EXPECT_NE(Float{"123"}, Float{456.789});

            EXPECT_EQ("123", Float{123}.toString());
            EXPECT_EQ("123.456", Float{123.456}.toString());
            EXPECT_EQ("-123", Float{-123}.toString());
            EXPECT_EQ("0.456", Float{.456}.toString());
            EXPECT_EQ("-123.456", Float{-123.456}.toString());
            EXPECT_EQ("-0.456", Float{-.456}.toString());
            EXPECT_EQ("2e08", Float{2E8}.toString());
            EXPECT_EQ("2e08", Float{2E+8}.toString());
            EXPECT_EQ("2e08", Float{2E+008}.toString());
            EXPECT_EQ("-2e08", Float{-2E8}.toString());
            EXPECT_EQ("2e-08", Float{2E-8}.toString());
            EXPECT_EQ("2e-08", Float{2E-008}.toString());
            EXPECT_EQ("-2e-08", Float{-2E-8}.toString());

            auto successful = value.setValue("123");
            EXPECT_TRUE(successful);
            EXPECT_EQ(value.value(), 123.0f);
            EXPECT_EQ(value.toString(), "123");
            EXPECT_TRUE(value.isValid());

            successful = value.setValue("456.789.123");
            EXPECT_FALSE(successful);
            EXPECT_EQ(value.value(), 123.0f);           // still the old value
            EXPECT_EQ(value.toString(), "123");
            EXPECT_TRUE(value.isValid());

            successful = value.setValue(".567");
            EXPECT_TRUE(successful);
            EXPECT_NEAR(value.value(), .567f, 0.001f);
            EXPECT_EQ(value.toString(), "0.567");
            EXPECT_TRUE(value.isValid());
        }

        TEST(PayploadDataTypes, Boolean) {
            // Booleans must be converted to the string literals “true” or “false”
            // Representation is case sensitive, e.g. “TRUE” or “FALSE” are not valid payloads.
            // An empty string (“”) is not a valid payload
            auto value = Boolean{false};

            EXPECT_TRUE(value.validateValue("true"));
            EXPECT_TRUE(value.validateValue("false"));
            EXPECT_FALSE(value.validateValue("True"));
            EXPECT_FALSE(value.validateValue("False"));
            EXPECT_FALSE(value.validateValue("TRUE"));
            EXPECT_FALSE(value.validateValue("FALSE"));
            EXPECT_FALSE(value.validateValue("0"));
            EXPECT_FALSE(value.validateValue("1"));
            EXPECT_FALSE(value.validateValue("123"));
            EXPECT_FALSE(value.validateValue("123.456"));
            EXPECT_FALSE(value.validateValue("abc"));
            EXPECT_FALSE(value.validateValue("-"));
            EXPECT_FALSE(value.validateValue(""));
            EXPECT_FALSE(value.validateValue(" "));

            EXPECT_EQ(Boolean{"true"}, Boolean{true});
            EXPECT_EQ(Boolean{"false"}, Boolean{false});
            EXPECT_NE(Boolean{"true"}, Boolean{false});
            EXPECT_NE(Boolean{"false"}, Boolean{true});

            EXPECT_EQ("true", Boolean{true}.toString());
            EXPECT_EQ("false", Boolean{false}.toString());

            auto successful = value.setValue("true");
            EXPECT_TRUE(successful);
            EXPECT_EQ(value.value(), true);
            EXPECT_EQ(value.toString(), "true");
            EXPECT_TRUE(value.isValid());

            successful = value.setValue("FALSE");
            EXPECT_FALSE(successful);
            EXPECT_EQ(value.value(), true);           // still the old value
            EXPECT_EQ(value.toString(), "true");
            EXPECT_TRUE(value.isValid());

            successful = value.setValue("false");
            EXPECT_TRUE(successful);
            EXPECT_EQ(value.value(), false);
            EXPECT_EQ(value.toString(), "false");
            EXPECT_TRUE(value.isValid());
        }

        TEST(PayploadDataTypes, Enumeration) {
            // Enum payloads must be one of the values specified in the format definition of the property
            // Enum payloads are case sensitive, e.g. “Car” will not match a format definition of “car”
            // Payloads should have leading and trailing whitespace removed
            // An empty string (“”) is not a valid payload
            auto value = Enumeration{{"Red", "Green", "Blue", " White ", "blue and green"}};

            EXPECT_TRUE(value.validateValue("Red"));
            EXPECT_TRUE(value.validateValue("Green"));
            EXPECT_TRUE(value.validateValue("Blue"));
            EXPECT_TRUE(value.validateValue("White"));
            EXPECT_TRUE(value.validateValue("blue and green"));
            EXPECT_FALSE(value.validateValue("red"));
            EXPECT_FALSE(value.validateValue("RED"));
            EXPECT_FALSE(value.validateValue("black"));
            EXPECT_FALSE(value.validateValue(""));
            EXPECT_FALSE(value.validateValue(" "));

            EXPECT_TRUE(value.value() == "");
            EXPECT_FALSE(value.isValid());

            auto successful = value.setValue("Red");
            EXPECT_TRUE(successful);
            EXPECT_TRUE(value.value() == "Red");
            EXPECT_TRUE(value.toString() == "Red");
            EXPECT_TRUE(value.isValid());
           
            successful = value.setValue("black");
            EXPECT_FALSE(successful);
            EXPECT_TRUE(value.value() == "Red");
            EXPECT_TRUE(value.toString() == "Red");
            EXPECT_TRUE(value.isValid());

            successful = value.setValue("blue and green");
            EXPECT_TRUE(successful);
            EXPECT_TRUE(value.value() == "blue and green");
            EXPECT_TRUE(value.toString() == "blue and green");
            EXPECT_TRUE(value.isValid());
        }

        TEST(PayploadDataTypes, Color_RGB) {
            // Color payload validity varies depending on the property format definition of either “rgb” or “hsv”
            // Both payload types contain comma separated whole numbers of differing restricted ranges
            // The encoded string may only contain whole numbers and the comma character “,”, no other characters are permitted, including spaces (” “)
            // Payloads for type “rgb” contains 3 comma separated values of numbers with a valid range between 0 and 255. e.g. 100,100,100
            // Payloads for type “hsv” contains 3 comma separated values of numbers. The first number has a range of 0 to 360, the second and third numbers have a range of 0 to 100. e.g. 300,50,75
            // An empty string (“”) is not a valid payload
            auto value = Color{ColorFormat::RGB};
            EXPECT_TRUE(value.validateValue("0,0,0"));
            EXPECT_TRUE(value.validateValue("1,1,1"));
            EXPECT_TRUE(value.validateValue("255,255,255"));
            EXPECT_FALSE(value.validateValue(""));
            EXPECT_FALSE(value.validateValue("0, 0, 0"));
            // EXPECT_FALSE(value.validateValue("0,,0"));        // <- Is handled as 0,0,0. Not sure if I should really dismiss this value
                                                                // Next test case to ensure this behaviour
            auto a = Color{ColorFormat::RGB, "1,,3"};
            auto b = Color{ColorFormat::RGB, ColorTuple{1,0,3}};
            EXPECT_TRUE(a == b);
            EXPECT_FALSE(value.validateValue("0,0,0,"));
            EXPECT_FALSE(value.validateValue("0.0.0"));
            EXPECT_FALSE(value.validateValue("0.2,0.3,4.5"));
            EXPECT_FALSE(value.validateValue("-1,0,0"));
            EXPECT_FALSE(value.validateValue("0,-1,0"));
            EXPECT_FALSE(value.validateValue("0,0,-1"));
            EXPECT_FALSE(value.validateValue("256,0,0"));
            EXPECT_FALSE(value.validateValue("0,256,0"));
            EXPECT_FALSE(value.validateValue("0,0,256"));

            auto c = Color{ColorFormat::RGB, ColorTuple(4,5,6)};
            EXPECT_TRUE(a != c);

            {
                auto d = Color{ColorFormat::RGB, ColorTuple(1,2,3)};
                EXPECT_TRUE("1,2,3" == d.toString());
            }
            {
                auto d = Color{ColorFormat::RGB, "1,,4"};
                EXPECT_TRUE("1,0,4" == d.toString());
            }

            {   
                auto successful = value.setValue("67,78,112");
                EXPECT_TRUE(successful);
                EXPECT_TRUE(value.value() == ColorTuple(67,78,112));
                EXPECT_TRUE(value.toString() == "67,78,112");
                EXPECT_TRUE(value.isValid());

                successful = value.setValue("300,78,112");
                EXPECT_FALSE(successful);
                EXPECT_TRUE(value.value() == ColorTuple(67,78,112));
                EXPECT_TRUE(value.toString() == "67,78,112");
                EXPECT_TRUE(value.isValid());

                successful = value.setValue("67,100,112");
                EXPECT_TRUE(successful);
                EXPECT_TRUE(value.value() == ColorTuple(67,100,112));
                EXPECT_TRUE(value.toString() == "67,100,112");
                EXPECT_TRUE(value.isValid());
            }
        }
    
        TEST(PayploadDataTypes, Color_HSV) {
            // Color payload validity varies depending on the property format definition of either “rgb” or “hsv”
            // Both payload types contain comma separated whole numbers of differing restricted ranges
            // The encoded string may only contain whole numbers and the comma character “,”, no other characters are permitted, including spaces (” “)
            // Payloads for type “rgb” contains 3 comma separated values of numbers with a valid range between 0 and 255. e.g. 100,100,100
            // Payloads for type “hsv” contains 3 comma separated values of numbers. The first number has a range of 0 to 360, the second and third numbers have a range of 0 to 100. e.g. 300,50,75
            // An empty string (“”) is not a valid payload
            auto value = Color{ColorFormat::HSV};
            EXPECT_TRUE(value.validateValue("0,0,0"));
            EXPECT_TRUE(value.validateValue("1,1,1"));
            EXPECT_TRUE(value.validateValue("360,100,100"));
            EXPECT_FALSE(value.validateValue(""));
            EXPECT_FALSE(value.validateValue("0, 0, 0"));
            // EXPECT_FALSE(value.validateValue("0,,0"));        // <- Is handled as 0,0,0. Not sure if I should really dismiss this value
                                                                // Next test case to ensure this behaviour
            auto a = Color{ColorFormat::HSV, "1,,3"};
            auto b = Color{ColorFormat::HSV, ColorTuple{1,0,3}};
            EXPECT_TRUE(a == b);
            EXPECT_FALSE(value.validateValue("0,0,0,"));
            EXPECT_FALSE(value.validateValue("0.0.0"));
            EXPECT_FALSE(value.validateValue("0.2,0.3,4.5"));
            EXPECT_FALSE(value.validateValue("-1,0,0"));
            EXPECT_FALSE(value.validateValue("0,-1,0"));
            EXPECT_FALSE(value.validateValue("0,0,-1"));
            EXPECT_FALSE(value.validateValue("361,0,0"));
            EXPECT_FALSE(value.validateValue("0,101,0"));
            EXPECT_FALSE(value.validateValue("0,0,101"));

            auto c = Color{ColorFormat::HSV, ColorTuple(4,5,6)};
            EXPECT_TRUE(a != c);

            {
                auto d = Color{ColorFormat::HSV, ColorTuple(1,2,3)};
                EXPECT_TRUE("1,2,3" == d.toString());
            }
            {
                auto d = Color{ColorFormat::HSV, "1,,4"};
                EXPECT_TRUE("1,0,4" == d.toString());
            }

            {   
                auto successful = value.setValue("67,78,55");
                EXPECT_TRUE(successful);
                EXPECT_TRUE(value.value() == ColorTuple(67,78,55));
                EXPECT_TRUE(value.toString() == "67,78,55");
                EXPECT_TRUE(value.isValid());

                successful = value.setValue("300,78,112");
                EXPECT_FALSE(successful);
                EXPECT_TRUE(value.value() == ColorTuple(67,78,55));
                EXPECT_TRUE(value.toString() == "67,78,55");
                EXPECT_TRUE(value.isValid());

                successful = value.setValue("67,100,55");
                EXPECT_TRUE(successful);
                EXPECT_TRUE(value.value() == ColorTuple(67,100,55));
                EXPECT_TRUE(value.toString() == "67,100,55");
                EXPECT_TRUE(value.isValid());
            }
        }
    }
}