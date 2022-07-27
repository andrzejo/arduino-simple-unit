import * as parser from "fast-xml-parser";
import {get} from "lodash";
import {fetchTestCaseReport, ReportDefinition, TestCaseReportDefinition} from "../../api";
import moment from "moment";

export type AsuReport = {
    props: { [key: string]: string },
    date: string,
    tests: TestCaseReportDefinition[]
}

type ReportProps = {
    get: (prop: string, def: any) => string | [] | object;
    getArray: (prop: string) => Array<any>;
}

const reportProps = (report: ReportDefinition): ReportProps => {
    return {
        get: (prop: string, def = null) => {
            return get(report, prop, def);
        },
        getArray: (prop: string): Array<any> => {
            const val = get(report, prop, []);
            if (Array.isArray(val)) {
                return val;
            }
            if (val) {
                return [val as object];
            }
            return [];
        }
    }
}

const getProps = (rep: ReportProps): {} => {
    return rep.getArray("testsuite.properties.property").reduce((acc, curr) => {
        acc[curr['@name']] = curr['@value'];
        return acc;
    }, {});
}

const getReportName = (value: string | null | undefined): string => {
    if (value) {
        return "asu-reports/" + value.trim() + ".json";
    }
    return "";
};

const getTests = async (rep: ReportProps, {}: {} = {}): Promise<TestCaseReportDefinition[]> => {
    const testsObjects = rep.getArray("testsuite.testcase");
    const tests: TestCaseReportDefinition[] = [];
    for (const t of testsObjects) {
        let name = t['@name'];
        const reportName = getReportName(name);
        try {
            const p = await fetchTestCaseReport(reportName);
            tests.push(p);
        } catch (e) {
            tests.push({
                success: -1,
                failed: 0,
                skipped: 0,
                duration: 0,
                result: false,
                tests: [],
                testCase: String(name || "").trim().replace(/^test_/, "")
            });
            console.error("Failed to fetch report " + reportName, e);
        }
    }
    return tests;
}

const getTimestamp = (rep: ReportProps): string => {
    const stamp = rep.get("testsuite.@timestamp", null);
    if (stamp) {
        return moment(stamp, "X").format('YYYY-MM-DD HH:mm:ss');
    }
    return ""
};

export const transformReportToAsuReport = async (reportXml: string): Promise<AsuReport> => {
    const options = {
        ignoreAttributes: false,
        attributeNamePrefix: "@"
    };
    const report = parser.parse(reportXml, options);
    const rep = reportProps(report);
    const date = getTimestamp(rep);
    const props = getProps(rep);
    const tests = await getTests(rep);
    return {
        date,
        props,
        tests
    };
}


