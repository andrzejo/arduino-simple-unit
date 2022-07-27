import * as React from "react";
import {useEffect, useState} from "react";
import {fetchReport} from "../api";
import Error from "./Error";
import {AsuReport, transformReportToAsuReport} from "../Lib/aus/asuReport";
import Header from "./Header";
import TestCase from "./TestCase";

import "./Report.scss"

type Props = {
    props: { [key: string]: string }
}

const PropsItem: React.FunctionComponent<Props> = (props) => {
    const values = [];
    for (let k in props.props) {
        values.push({name: k, value: props.props[k]})
    }
    return (
        <div className={"report-props"}>
            <div className={"prop-title"}>
                Report props
            </div>
            <div className={"prop-list"}>
                {values.map((v, idx) =>
                    <div key={idx}>
                        <div className={"prop-name"}>{v.name}</div>
                        <div className={"prop-value"}>{v.value}</div>
                    </div>
                )}
            </div>
        </div>
    )
}

const Report: React.FunctionComponent = () => {
    const [report, setReport] = useState<AsuReport>();
    const [error, setError] = useState<string>("");

    useEffect(() => {
        fetchReport()
            .then((r) => {
                transformReportToAsuReport(r)
                    .then(asuReport => {
                        setReport(asuReport);
                    })
                    .catch(e => setError("Failed to get asu report: " + e.toString()));
            })
            .catch(e => setError("Failed to fetch report: " + e.toString()));
    }, [])

    return (
        <div className={"report"}>
            {error && <Error error={error}/>}
            {report && <Header report={report}/>}
            <div className={"test-label"}>
                <div className={"label"}>Test case list</div>
                <div className={"cases"}>({(report && report.tests) ? report.tests.length : 0} test cases)</div>
            </div>
            {report && report.tests && report.tests.map((t, idx) => <TestCase test={t} key={idx}/>)}
            {report && <PropsItem props={report.props}/>}
        </div>
    )
}

export default Report