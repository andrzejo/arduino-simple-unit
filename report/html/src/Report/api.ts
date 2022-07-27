import axios from 'axios';

export type ReportDefinition = {
    [key: string]: string | object
};

export type FailedDefinition = {
    expected: string
    actual: string,
    message: string,
    file: string,
    line: number
};

export type TestDefinition = {
    name: string,
    success: boolean,
    disabled: boolean,
    assertions: number,
    failedAssertions: number,
    messages: string[],
    artifacts: string[],
    failed: FailedDefinition[]
};

export type TestCaseReportDefinition = {
    testCase: string,
    result: boolean,
    success: number,
    failed: number,
    skipped: number,
    duration: number,
    tests: TestDefinition[]
};

export const fetchReport = (): Promise<string> => {
    return axios.get("CTestResults.xml").then(r => r.data)
}

export const fetchTestCaseReport = (name: string): Promise<TestCaseReportDefinition> => {
    return axios.get(name).then(r => r.data)
}