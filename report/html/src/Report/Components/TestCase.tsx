import * as React from "react";
import {TestCaseReportDefinition, TestDefinition} from "../api";

import "./TestCase.scss"
import duration from "../Utils/duration";

type Props = {
    test: TestCaseReportDefinition
}

type TestProps = {
    test: TestDefinition
}

const getStatus = (test: TestDefinition) => {
    if (test.disabled) {
        return "SKIPPED";
    }
    if (test.success) {
        return "SUCCESS";
    }
    return "FAILED";
};

const getFailedAssertions = (test: TestDefinition) => {
    if (test.failedAssertions == 0) {
        return 0;
    }
    return (
        test.failed.map((f, idx) => <div key={idx}>
                <div><strong>'{f.expected}'</strong> != <strong>'{f.actual}'</strong></div>
                <pre>{f.message}</pre>
                <pre>File: <strong>{f.file}:{f.line}</strong></pre>
            </div>
        )
    );
}

const getDetails = (test: TestDefinition) => {
    const baseName = (str: string) => {
        return String(str).substring(str.lastIndexOf('/') + 1);
    };

    const artifacts = test.artifacts.map(baseName);
    if (artifacts.length) {
        return (
            artifacts.map((f, idx) =>
                <img key={idx} alt={f} src={"asu-resources/" + f}/>
            )
        );
    }
    return ""
}

const Test: React.FunctionComponent<TestProps> = (props) => {
    const {test} = props;
    const status = getStatus(test);

    return (
        <div className={"row single-test " + (status.toLocaleLowerCase())}>
            <div className={"test-name"}>{test.name}</div>
            <div className={"status"}>{status}</div>
            <div className={"assertions"}>{test.assertions}</div>
            <div className={"failed-assertions"}>{getFailedAssertions(test)}</div>
            <div className={"details"}>{getDetails(test)}</div>
        </div>
    )
};

const TestCase: React.FunctionComponent<Props> = (props) => {
    const {test} = props;
    return (
        <div className={"testcase"}>
            {test.success == -1 && <div className={"failed-to-load"}>
                <div>Failed to load test result for <b>{test.testCase}</b></div>
            </div>}

            {test.success > -1 && <div className={"container"}>
                <div className={"testcase-header"}>
                    <div className={"case-name"}>{test.testCase}</div>
                    <div className={"table"}>
                        <div className={"row head"}>
                            <div>Success</div>
                            <div>Failed</div>
                            <div>Skipped</div>
                            <div>Duration</div>
                        </div>
                        <div className={"row"}>
                            <div>{test.success}</div>
                            <div>{test.failed}</div>
                            <div>{test.skipped}</div>
                            <div>{duration(test.duration)}</div>
                        </div>
                    </div>
                </div>
                <div className={"tests"}>
                    <div className={"table"}>
                        <div className={"row head"}>
                            <div>Test</div>
                            <div>Status</div>
                            <div>Assertions</div>
                            <div>Failed assertions</div>
                            <div>Details</div>
                        </div>
                        {test.tests && test.tests.map((t, idx) => <Test key={idx} test={t}/>)}
                    </div>
                </div>
            </div>}
        </div>
    )
}

export default TestCase