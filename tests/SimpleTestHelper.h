/**
* -------------------------------------------------------
* Copyright (c) 2025 Thomas Ray
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
* copies of the Software, and to permit persons to whom the Software is furnished
* to do so, subject to the following conditions :
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
* FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR
* COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
* IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
* CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
* -------------------------------------------------------
* SimpleTestHelper.h
* -------------------------------------------------------
* Simple manual test logging helpers for Catch2 tests
* -------------------------------------------------------
*/
#pragma once

#include "TestLogger.h"
#include <chrono>
#include <string>

namespace TestUtils
{
    /**
     * @brief RAII helper for automatic test case logging
     *
     * This class automatically logs the start and end of a test case.
     * Use the TEST_CASE_LOG macro at the beginning of your test cases.
     */
    class TestCaseLogger
    {
    public:
        explicit TestCaseLogger(const std::string& testName, const std::string& tags = "")
            : m_TestName(testName), m_StartTime(std::chrono::steady_clock::now())
        {
            TestLogger::GetInstance().LogTestStart(testName);
            if (!tags.empty())
            {
                TestLogger::GetInstance().Log(LogLevel::Info, "TEST", "Tags: " + tags);
            }
        }

        ~TestCaseLogger()
        {
            auto endTime = std::chrono::steady_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime);

            TestLogger::GetInstance().Log(LogLevel::Info, "TEST",
                "Test case '" + m_TestName + "' completed in " + std::to_string(duration.count()) + "ms");
            TestLogger::GetInstance().LogTestEnd(m_TestName, true); // Assume passed for now
        }

    private:
        std::string m_TestName;
        std::chrono::steady_clock::time_point m_StartTime;
    };

    /**
     * @brief RAII helper for automatic section logging
     *
     * This class automatically logs the start and end of a test section.
     * Use the SECTION_LOG macro at the beginning of your sections.
     */
    class SectionLogger
    {
    public:
        explicit SectionLogger(const std::string& sectionName)
            : m_SectionName(sectionName)
        {
            TestLogger::GetInstance().LogSection(sectionName);
        }

        ~SectionLogger()
        {
            TestLogger::GetInstance().Log(LogLevel::Info, "SECTION", "End of section: " + m_SectionName);
        }

    private:
        std::string m_SectionName;
    };
}

// Convenience macros for test logging
#define TEST_CASE_LOG(testName, tags) \
    TestUtils::TestCaseLogger _testCaseLogger(testName, tags)

#define SECTION_LOG(sectionName) \
    TestUtils::SectionLogger _sectionLogger(sectionName)

// Simple assertion logging - call this manually after assertions
#define LOG_ASSERTION(expression, result, message) \
    TestUtils::TestLogger::GetInstance().Log(TestUtils::LogLevel::Info, "ASSERTION", \
        std::string(expression) + " -> " + (result ? "PASS" : "FAIL") + ": " + std::string(message))

// Test execution macros
#define LOG_TEST_START(name) \
    TestUtils::TestLogger::GetInstance().LogTestStart(name)

#define LOG_TEST_END(name, passed) \
    TestUtils::TestLogger::GetInstance().LogTestEnd(name, passed)

// Information logging
#define LOG_TEST_INFO(message) \
    TestUtils::TestLogger::GetInstance().Log(TestUtils::LogLevel::Info, "TEST", message)

#define LOG_TEST_WARN(message) \
    TestUtils::TestLogger::GetInstance().Log(TestUtils::LogLevel::Warning, "TEST", message)

#define LOG_TEST_ERROR(message) \
    TestUtils::TestLogger::GetInstance().Log(TestUtils::LogLevel::Error, "TEST", message)

/**
 * @brief Macro to initialize test logging at the start of main
 *
 * Add this macro at the very beginning of your test main function
 * to initialize the test logging system.
 */
#define INIT_TEST_LOGGING() \
    TestUtils::TestLogger::GetInstance().Initialize("TestOutput.log")
